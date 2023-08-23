# asbr_messageInfo_sheet2json
This tool is for the modding of _[JoJo's Bizarre Adventure: All-Star Battle R](https://www.nexusmods.com/jojosbizarreadventureallstarbattler)_, a 2022 game developed by [CyberConnect2](https://jojowiki.com/CyberConnect2).

It enables you to swiftly convert spreadsheet data into a JSON format, which can then be converted into a binary file that the game can understand.
There's quite a bit of set-up you need to do first however...

Note that you will need to understand how the different values of an ASBR `messageInfo.bin.xfbin` file work to set up your data correctly.
(That being said, I will be working on a few tools to make this process easier to newer modders.)

If you are new to ASBR modding and want to learn more, join the [JoJo's Bizarre Modding Community on Discord](https://discord.gg/asbr-eoh-modding-community-608029171800735744) and find me `@kojobailey`.

## Installation
1. Download the latest release from the [Releases](https://github.com/KojoBailey/asbr_messageInfo_sheet2json/releases/latest) page, or download it from Nexus Mods (coming soon).
2. Ensure that you have both `mI to JSON.exe` and `settings.cfg`.
3. Drag&Drop the file you want to convert! Ensure that the formatting is correct by following the following guide:

## Usage Guide
### Formatting the spreadsheet correctly
It is important that you spreadsheet has the following columns, in this order:
1. `msg_id_crc32` - STRING - The endian-swapped CRC-32/BZIP2 ID of the string's corresponding audio ID (e.g., `1dio01_btlst_00_3dio01` = `32A8575F`).
2. `char_id` - INTEGER - The character's ID corresponding int ID (e.g., Dio Brando = `4`).
3. `cue_id` - INTEGER - The cue number for the string's attached audio ID, found in ACBs/AWBs.
4. `string` - STRING - The message itself. Ensure that the formatting is good for JSON (e.g., use `\"` instead of just `"` to avoid JSON errors).
Below is an image example:

**TO BE CONTINUED**
