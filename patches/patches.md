# Patches for QPang

These are patches that alter the game's execution after being applied to the game's executable.

## How to apply a patch

1. Download x64dbg (https://x64dbg.com)
2. Run x32dbg.exe (it comes with the x64dbg install and is used for 32-bit applications)
3. Open QPangBin.exe (File -> Open)
4. Open the patch window (CTRL + P  or File -> Patch File)
5. Add patch(es) by clicking on "Import", when succesful it should say "x/x patches applied" for every patch added, for other alerts see below.
6. Save the result by clicking on "Patch file" and saving as a .exe

### Note for hackshield patches

Patches that disable hackshield require you to rename the HSHield-folder to something else, for example HSHieldPatched.

##  Issues and alerts

### Some bytes do not match the original in the patch file

When you get this alert, it means you're using a patch for the wrong executeable-version.

Verify that you're using the right install and patch (2012 or 2009, every patch includes the version in the name) and make sure that the executable hasn't been patched with that specific patch yet.

### Other problems/alerts

If something doesn't work as expected or a patch can't be applied even though it's the correct version, please contact us.


## Credits

QpangReborn
Deluze
Dennis

