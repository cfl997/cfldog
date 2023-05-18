# cfldog - 软件加密狗[![License](https://img.shields.io/badge/license-Apache2.0-green)](https://github.com/cfl997/cfldog/blob/main/LICENSE)

cfldog 是一个用于生成唯一机器码、生成许可码并验证许可的软件加密狗工具。

## 功能特点

- 生成唯一的机器码，用于标识每台机器。
- 可以自定义字符，并生成相应的 GeneralDogKeyD.key 文件。
- 使用 AES 加密算法对 GeneralDogKeyD.key 进行加密，生成许可码 cflLisence.key。
- 许可码中包含时效信息（年、月、星期），用于限制许可的有效期。
- 可以通过判断许可码是否匹配当前机器、是否在有效期内以及是否包含自定义字符串来验证许可。

## 安装和配置

1. 克隆或下载项目到本地计算机。
2. 使用了cryptopp870 https://www.cryptopp.com/ lib中包含release 的cryptlib.lib 
3. 在 Windows 10 或 Windows Server 2012 上进行测试。
4. 尚未进行 Linux 上的测试。

## 使用示例

1. 在需要加密的机器上，运行 GeneralDogKey.exe 工具，生成唯一机器码：`GeneralDog.key`
2. 在自己许可的机器上，运行GeneralLicenseD.exe工具，生成唯一机器码：`cflLisence.key`
3. 将生成的 `cflLisence.key` 文件嵌入你的软件中。
4. 在软件中使用 GeneralCFLDog.lib库进行许可判定：`isSameLicense`

## 贡献指南

感谢你考虑为 该项目 做贡献！如果你想报告问题、提出功能请求或提交补丁，请按照以下步骤：

1. 在 GitHub 上 fork 这个项目。
2. 创建一个新的分支并进行修改。
3. 提交你的修改并创建一个新的 Pull Request。

## 授权信息

cfldog 项目使用 [MIT 许可证](LICENSE)。

## 联系方式

如有任何问题或疑问，请联系作者：

- 姓名: [CaoFulei]
- 邮件: [cfl997@163.com]
- VX:[cfl997]

[![Discord](https://img.shields.io/badge/cfl997%20Server--blue.svg?style=social&logo=Discord)]( https://discord.gg/nTRQ5uHuJS)

