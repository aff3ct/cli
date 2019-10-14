# CLI: Command-line interface

**CLI** is a rich **command-line interface** library that has been extracted
from its original project, namely [AFF3CT](https://aff3ct.github.io). At this
time this project is not documented.

## Installation

First make sure to have installed a `C++11 compiler`, `CMake` and `Git`. Then
install **CLI** by running:

```bash
git clone --recursive https://github.com/aff3ct/cli.git
mkdir cli/build
cd cli/build
cmake .. -DCMAKE_BUILD_TYPE="Release"
make -j4
```
