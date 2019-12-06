DFU步骤：

1.编译app文件，运行bootsettings-make.bat，生成bootsettings

2.运行app-sd-bl-bs-full.bat文件生成Bootloader_MegaEEG_V_full_release.hex

3.通过nrf connect下载Bootloader_MegaEEG_V_full_release.hex文件到板子中

运行app-dfu-zip.bat，生成DFU包，传到手机进行DFU

(   也可以nrfjprog --program Bootloader_MegaEEG_V_full_release.hex

nrfjprog --reset  )



bootloader编译



首先运行app-dfu-zip.bat生成zip文件，然后解压该压缩包，然后运行dfu-copy.py

后续所有的app下载不能直接keil下载必须通过  dfu-copy.py  脚本下载



![1574676518121](C:\Users\acer\AppData\Roaming\Typora\typora-user-images\1574676518121.png)