# Zippy
CL application to process zip archives - read/check content/write

ASAP zip-archivator for terminal.<br>
Usage example:```zippy -otest.zip -amain.cpp,header.h,source.cpp -edoc.txt -dnewdir -l```

Argument order is free, so it doesn't matter if you write files to add first and then path to zip archive,<br>
but you always need to write path to zip archive - the only rule that exists in this application.<br>

### List of arguments
```-o``` - open zip archive<br>
```-a``` - takes list of files to add<br>
```-e``` - takes list of files to extract<br>
```-d``` - directory, where files will be extracted<br>
```-l``` - show archive content<br>
