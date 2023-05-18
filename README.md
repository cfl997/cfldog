# cfldog - Software Encryption Dongle [![License](https://img.shields.io/badge/license-Apache2.0-green)](https://github.com/cfl997/cfldog)

cfldog is a software encryption dongle tool that generates unique machine codes, creates license codes, and verifies licenses.

## Features

- Generates unique machine codes to identify each machine.
- Allows customization of characters and generates corresponding GeneralDogKeyD.key file.
- Encrypts the GeneralDogKeyD.key file using AES encryption algorithm to generate the license code cflLicense.key.
- The license code includes time-based validity information (year, month, week) to restrict the license's expiration.
- Validates the license by checking if it matches the current machine, is within the validity period, and contains the custom string.

## Installation and Configuration

1. Clone or download the project to your local machine.
2. Make sure to include `cryptopp870` from https://www.cryptopp.com/ with the `cryptlib.lib` release included.
3. Tested on Windows 10 and Windows Server 2012.
4. Not yet tested on Linux.

## Usage Example

1. Run the `GeneralDogKey.exe` tool on the machine that needs encryption to generate a unique machine code: `GeneralDog.key`.
2. Run the `GeneralLicenseD.exe` tool on the licensed machine to generate a unique machine code: `cflLicense.key`.
3. Embed the generated `cflLicense.key` file into your software.
4. Use the `GeneralCFLDog.lib` library in your software to perform license verification: `isSameLicense`.

## Contributing

Thank you for considering contributing to this project! If you would like to report issues, request features, or submit patches, please follow these steps:

1. Fork the project on GitHub.
2. Create a new branch and make your modifications.
3. Submit your modifications and create a new pull request.

## License

The cfldog project is licensed under the [Apache License 2.0](LICENSE).

## Contact

For any questions or inquiries, please contact the author:

- Name: [Cao Fulei]
- Email: [cfl997@163.com]
- VX: [cfl997]

[![Discord](https://img.shields.io/badge/cfl997%20Server--blue.svg?style=social&logo=Discord)](https://discord.gg/nTRQ5uHuJS)
