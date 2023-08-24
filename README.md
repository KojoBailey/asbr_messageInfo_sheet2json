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
Note that you should **not** have header titles.

Below is an image example:

![image](https://github.com/KojoBailey/asbr_messageInfo_sheet2json/assets/50509420/ea66daa3-39d2-4ec9-90b9-7051661d3e12)

There is also a 5th, optional column you can add, but more on that further down.

### Exporting the spreadsheet as a 'character-separated values' file
These files have the data separated by a single character.
The most common of these is CSV (comma-separated values), but you shouldn't use this format for this tool as your strings will most likely contain commas as well, messing up the file in some situations.
Instead, I recommend TSV (tab-separated values) if your software can export to it (Google Sheets can, for example).

Once you have the file exported, feel free to replace the separating character - aka the "delimiter" - with whatever you want. This can be done in a lot of text editors, such as [Notepad](https://www.computerhope.com/issues/ch001605.htm#notepad) and [Visual Studio Code](https://code.visualstudio.com/docs/editor/codebasics#_find-and-replace). Personally, I use the `@` symbol since it doesn't appear in any ASBR `messageInfo` strings.

### Configuring the tool's settings
The ZIP containing the `mI to JSON.exe` also comes with a `settings.cfg` file. This file has 3 parameters:
- `file_extension` - STRING - `.tsv` by default → The file extension of the file you want to input. Anything should be supported as long as the inner-contents are correctly formatted.
- `delimiter` - CHAR - `@` by default → The character that separates your data's "cells". This character shouldn't appear in any of your data.
- `compare_text` - BOOL - `0` (false) by default → This is an extra option for enabling a 5th column. See the XXXXX section for when and how to use it.

The tool doesn't allow much flexibility with the formatting of the CFG, so you should only change the parameter values and nothing else (e.g., don't add spaces between the `=` signs!). The only thing you should be good to change is the order of the parameters.

Alternatively, you can change the settings from the EXE itself, using the `/settings` command when prompted. Just remember to answer with valid data types.

If, when running the tool, you get some kind of white-coloured error, it means that either your input data or your settings are formatted incorrectly. Errors in red are ones I've manually added and should provide sufficient information on how to solve the issue that comes up.

### Inputting a file and recieving the output
As mentioned at the top, all you need to do is drag&drop your single input file onto the EXE.

If successful, the console should output `> Conversion complete! File has been output as 'output.json'.` and a file titled `output.json` will appear in the same directory as the EXE.

If you have any blank cells in your data, they will be output as either `"empty_string"` or `0` (depending on the data type).

### Using `compare_text`
When set to `1` (true), the `compare_text` boolean variable allows for a 5th column to be included in your data, this being another list of dialogue strings like the 4th column.

What this does is compare the data in the 4th column against that of the 5th column. If the 4th column for a row, the string in the 5th column will instead be used. This feature was really just added for really specific cases like my own (see below for an example:)

![image](https://github.com/KojoBailey/asbr_messageInfo_sheet2json/assets/50509420/17378612-a488-4c46-986a-f54f2f53adb5)
