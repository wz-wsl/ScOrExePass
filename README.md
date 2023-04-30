# ScOrExePass
这个项目是我几个月前写的了，还发出来了，现在去放到vt上测试，感觉都还行，只爆几个，就重新再github上发一下

这是我文章地址:https://forum.butian.net/share/1898

这是之前的效果(我是直接从我文章里截取的):
![1](https://github.com/wz-wsl/ScOrExePass/blob/main/pic/Screenshot_20230430_210850.jpg)

![2](https://github.com/wz-wsl/ScOrExePass/blob/main/pic/Screenshot_20230430_210901.jpg)
这是今天去vt测试看的
![3](https://github.com/wz-wsl/ScOrExePass/blob/main/pic/3.PNG)

1.shellcodeBypass使用:
把生成的shellcode放到py脚本里运行，将py生成的文件放到网站根目录下，在cpp文件里的wmain函数下把对应的端口和路径文件名改成你对应的网站端口和py生成的文件名，最后编译成exe，运行即可

2.Exebypass使用:
把exe转成shellcode，这里用到pe2shellcode这个项目(https://github.com/hasherezade/pe_to_shellcode)，将生成的shellcode文件放到网站根目录下，把wmain函数里的端口和文件名改成对应自己的，随后运行即可，具体分析可以看我文章https://forum.butian.net/share/1898

