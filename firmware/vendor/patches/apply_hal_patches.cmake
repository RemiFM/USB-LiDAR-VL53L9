# Applies the I3C polling fixes from stm32c5xx-hal-i3c-polling-bounds.patch (same folder)
# to ST's HAL copy in stm32c5xx_drivers/ (owned by STM32CubeMX2, which may replace
# it when the HAL pack is updated). Runs at CMake configure time:
#   - already patched     -> nothing to do
#   - original ST code    -> patch in place
#   - neither (HAL changed) -> stop with an error so the fix is never lost silently
#
# Without these fixes, polling-mode I3C transfers can read past the receive buffer
# and the control FIFO array, which corrupts LiDAR frames.

set(_hal_i3c ${CMAKE_CURRENT_LIST_DIR}/../../stm32c5xx_drivers/hal/stm32c5xx_hal_i3c.c)
file(READ ${_hal_i3c} _src)
set(_changed FALSE)

function(_hal_fix name original fixed)
  string(FIND "${_src}" "${fixed}" _has_fixed)
  string(FIND "${_src}" "${original}" _has_original)
  if(NOT _has_fixed EQUAL -1)
    return()
  elseif(NOT _has_original EQUAL -1)
    string(REPLACE "${original}" "${fixed}" _new "${_src}")
    set(_src "${_new}" PARENT_SCOPE)
    set(_changed TRUE PARENT_SCOPE)
    message(STATUS "HAL I3C fix applied: ${name}")
  else()
    message(FATAL_ERROR "HAL I3C fix '${name}': code not found in ${_hal_i3c}. "
      "The HAL was updated; re-check vendor/patches/stm32c5xx-hal-i3c-polling-bounds.patch.")
  endif()
endfunction()

# 1. HAL_I3C_CTRL_Transfer: a transfer that left any byte unsent/unreceived is an error.
_hal_fix("transfer completion check"
  "if ((hi3c->tx_count_byte != 0U) && (hi3c->rx_count_byte != 0U))"
  "if ((hi3c->tx_count_byte != 0U) || (hi3c->rx_count_byte != 0U))")

# 2. I3C_ReceiveByteTreatment: never write past the receive buffer.
_hal_fix("receive bounds"
  "  while (LL_I3C_IsActiveFlag_RXFNE(p_i3cx) != 0U)\n  {\n    *hi3c->p_rx_data = LL_I3C_ReceiveData8(p_i3cx);"
  "  while ((hi3c->rx_count_byte > 0U) && (LL_I3C_IsActiveFlag_RXFNE(p_i3cx) != 0U))\n  {\n    *hi3c->p_rx_data = LL_I3C_ReceiveData8(p_i3cx);")

# 3. I3C_ControlDataTreatment: CFNF is a level flag; don't read past the control array.
_hal_fix("control FIFO bounds"
  "  if (LL_I3C_IsActiveFlag_CFNF(p_i3cx) != 0U)\n  {\n    LL_I3C_WriteControlWord(p_i3cx, *hi3c->p_tc_data);"
  "  if ((hi3c->tc_count_word > 0U) && (LL_I3C_IsActiveFlag_CFNF(p_i3cx) != 0U))\n  {\n    LL_I3C_WriteControlWord(p_i3cx, *hi3c->p_tc_data);")

if(_changed)
  file(WRITE ${_hal_i3c} "${_src}")
endif()
# Re-run the check whenever the HAL file changes (e.g. after a CubeMX2 update).
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${_hal_i3c})
