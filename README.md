# gawspool_vm
This program will split VM printout txt files out of Hercules and, optionally, will convert them to PDF.

## The printjob splitter
For this to work, you download the gawspool_vm.c source to your computer and compile it with gcc. See to it that the resulting executable is in your path.

## The script file
There is a script file involved that will (optionally) be called by the printjob splitter, its name in prtpdf_vm. Place it in your path as well.

## Hercules configuration changes
There's a file called hercules.cnf.prt that contains the needed changes for my system. You will have to create a directory in your Hercules tree somewhere (preferably where the print files go now) and remember it to tailor the configuration file.

In your own hercules.cnf file duplicate the 000E line and comment out the top one to remember the original line so that you can revert to the old situation. Now copy the line from the **hercules.cnf.prt** file and put it into your own configuration file. You will have to make changes to accommodate your situation. Especially the line that reads:

  000E   1403   "|gawspool_vm ~/6PExt/urd/prtpdf/ prtpdf_vm"

contains a directory where gawspool_vm will drop its splitted .txt files. The directory you created must be substituted here, where "~/6PExt/urd/prtpdf/" is now. Be sure to end your directory name with a '/'...

## VM/CMS side
Regrettably at this time we have to make changes to CMS as well. Since VM does not generate an End-of-printjob seperator, we have to add one ourselves. We do that by creating our own PRINT command. Upload two files to CMS:
- SEP.PAGE.A will go into SPE PAGE A
- PINT.EXEC.A will go into PRINT EXEC A

## Result
Now, when you print, the new print exec will add a couple of seperator lines, that can be recognixed by the gawspool_vm program to spool the files neatly into sperate .txt files.
