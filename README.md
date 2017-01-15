[![Build Status Master](https://travis-ci.org/physycom/get_nominatim_info.png?branch=master)](https://travis-ci.org/physycom/get_nominatim_info "master")


### Installation
**Make** and a **C++11** compatible compiler are required. Also **wget** must be a recognized system command (if you're on Windows, try http://www.gnu.org/software/wget/).

Clone the repo and type ``make all`` in your favourite shell.

Uses jsoncons library (https://github.com/danielaparker/jsoncons).

### Usage
```
get_nominatim_info.exe -i input.json -o output.json -f [output style, 'a' (no quotes) for array or 'o' for object]
```
where *input.json* must be an existing and valid .json file, and must have "lat" and "lon" fields.

The optional -f specifies the style of the output json file (see below for an example). If omitted, the input file style will be preserved.

An *output.json* file will be created with the street information pulled from the chosen nominatim db.

### Input Sample

Either array-style:

```
[
    {
        "your_key1":"your_value",
        "your_key2":"your_value",
        "lat" : 44.498950,
        "lon" : 11.353606
    },
    {
        "your_key1":"your_value",
        "your_key2":"your_value",
        "lat" : 44.498595,
        "lon" : 11.354939
    },
    {
        "your_key1":"your_value",
        "your_key2":"your_value",
        "lat" : 44.498257,
        "lon" : 11.355894
    }
]
```

or object-style:

```
{
    "gps_record_0000001":
    {
        "your_field":"your_content",
        "lat":44.5021611,
        "lon":11.3648926
    },
    "gps_record_0000002":
    {
        "another_field":"another_content",
        "lat":44.5021381,
        "lon":11.3648768
    }
}
```


&copy; _Physics of Complex Systems Laboratory - Physics and Astronomy Department - University of Bologna_
