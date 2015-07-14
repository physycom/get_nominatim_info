### Installation
**Make** and a **C++11** compatible compiler are required. Also **wget** must be a recognized system command (if you're on Windows, try http://www.gnu.org/software/wget/).

Currently requires the included version of jsoncons library (https://github.com/danielaparker/jsoncons), and not any newer version.

Clone the repo and type ``make all`` in your favourite shell.

### Usage
```
get_nominatim_info.exe -i input.json -o output.json
```
where *input.json* must be an existing and valid .json file, and must have "lat" and "lon" fields. An *output.json* file will be created with the street information pulled from the chosen nominatim db.

### Input Sample

Either:

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

or:

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
