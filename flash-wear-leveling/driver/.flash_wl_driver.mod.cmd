savedcmd_flash_wl_driver.mod := printf '%s\n'   flash_wl_driver.o | awk '!x[$$0]++ { print("./"$$0) }' > flash_wl_driver.mod
