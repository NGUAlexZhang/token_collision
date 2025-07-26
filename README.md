# 口令字典生成器

## 使用方法
目前本项目中包含了很多shell脚本，因为是在linux环境下进行的开发，所以目前似乎也仅支持在linux环境下运行，且因为时间因素暂未编译windows版的，请见谅，请使用linux环境或者wsl运行。

首先进入项目根目录，执行
```shell
make all
```

然后，使用管理员模式执行安装
```shell
make install
```

如要卸载只需管理员模式执行
```shell
rm /usr/local/bin/pinyin
rm /usr/local/bin/frequency
rm /usr/lib/libsam.so
rm /usr/lib/libacam.so
```

完成安装后执行
```shell
chmod 755 ./scripts/*
./scripts/generate.sh
```
由于生成的字典可能会很大，所以可以随时中断此程序
已停止更新
