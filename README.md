---
documentclass: physycomen
title:  "get_nominatim_info"
author: "Di Cristina, Fabbri, Guidetti, Sinigardi"
---

<a href="http://www.physycom.unibo.it"> 
<div class="image">
<img src="https://cdn.rawgit.com/physycom/templates/697b327d/logo_unibo.png" width="90" height="90" alt="© Physics of Complex Systems Laboratory - Physics and Astronomy Department - University of Bologna"> 
</div>
</a>
<a href="https://travis-ci.org/physycom/get_nominatim_info"> 
<div class="image">
<img src="https://travis-ci.org/physycom/get_nominatim_info.png?branch=master" width="90" height="20" alt="Build Status"> 
</div>
</a>
<a href="https://ci.appveyor.com/project/cenit/get-nominatim-info"> 
<div class="image">
<img src="https://ci.appveyor.com/api/projects/status/sdqdclf6hyi5bhty?svg=true" width="90" height="20" alt="Build Status"> 
</div>
</a>


### Purpose
This tool queries a nominatim database to add street information to a .json file containing latitude and longitude entries. 

### Installation
**CMake** and a **C++11** compatible compiler are required. To build the executable, clone the repo and then type  
```
mkdir build ; cd build ; cmake .. ; cmake --build . --target install
```
With CMake you can also deploy projects for the most common IDEs.  
Contains [jsoncons](https://github.com/danielaparker/jsoncons) as a git submodule.

### Usage
```
get_nominatim_info.exe -i input.json -o output.json -f [output_style]
[output_style]: use 'a' (no quotes) for array or 'o' for object
```
where *input.json* must be an existing and valid .json file, and must have "lat" and "lon" fields.   
The optional -f specifies the style of the output json file (see below for an example). If omitted, the input file style will be preserved.   
An *output.json* file will be created with the street information pulled from the chosen nominatim db.   
More details about file formats is available [here](https://github.com/physycom/file_format_specifications/blob/master/formati_file.md).

