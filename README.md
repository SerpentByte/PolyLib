# PolyLib
Polymer generating libraries and a few other functions.
## Documentation
### Dependencies
C++ 9.0 and above</br>
make

### Installation
1.  Download the tar file. Extract to install location.
    tar -xf polylib.tar
    mv polylib <install location>
2.  cd <install location>/polylib
3.  make
4.  echo "export PATH=$PATH:<install location>/polylib/bin" >> ~/.bashrc
#### Example
1.  pwd
    /home/user/Downloads
2.  tar -xf polylib.tar
3.  mv polylib /home/user/programs
4.  cd /home/user/programs/polylib
5.  make
6.  echo "export PATH=$PATH:/home/user/programs/polylib/bin" >> ~/.bashrc
    
### Usage
If you type the command without any options, usage will be shown.
1.  **rnd** 
    rnd -beads \<integer\> -sig \<float\></br>
    |Essential flags|                                    |
    |--------------|------------------------------------|
    |-beads        |\<number of beads in the polymer\>  |
    |-sig          |\<size of one bead\>                | 
    
    |Optional flags            |                                                   |
    |-------------------------|---------------------------------------------------|
    |-o \<output\>            |Output file name \[default = out.gro\]              |
    |-bond \<value\>          |Manual bond distance \[default = sigma\]           |
    |-c                       |Center polymer inside box (overrides -centre)      |
    |-box \<a\> \<b\> \<c\>   |(a,b,c) are box side lengths \[default = (0,0,0)\] |
    |-centre \<x\> \<y\> \<z\>|Define center \[default (0,0,0)\]                   |
    |-avoid \<true/false\>    |Self avoiding beads \[default true\]               |
    |-nt                      |<number of CPU threads to use> \[default 1\]       |
    |-v                       |Verbose. Print parameters.                         |
    
    
 2. **box**
    box -beads \<integer\> -sig \<float\> -box \<float\> \<float\> \<float\></br>
    |Essential flags|                                                |
    |--------------|------------------------------------------------|
    |-beads        |\<number of beads in the polymer\>              |
    |-sig          |\<size of one bead\>                            |
    |-box          |\<a\> \<b\> \<c\> (a, b, c are box side lengths)|
    
    |Optional flags            |                                                   |
    |-------------------------|---------------------------------------------------|
    |-o \<output\>            |Output file name \[default = out.gro\]              |
    |-bond \<value\>          |Manual bond distance \[default = sigma\]           |
    |-c                       |Center polymer inside box (overrides -centre)      |
    |-box \<a\> \<b\> \<c\>   |(a,b,c) are box side lengths \[default = (0,0,0)\] |
    |-centre \<x\> \<y\> \<z\>|Define center \[default (0,0,0)\]                   |
    |-avoid \<true/false\>    |Self avoiding beads \[default true\]               |
    |-nt                      |<number of CPU threads to use> \[default 1\]       |
    |-v                       |Verbose. Print parameters.                         |
  
  
3. **sph**
    sph -beads \<integer\> -sig \<float\> -r \<float\></br>
    |Essential flags|                                                |
    |--------------|------------------------------------------------|
    |-beads        |\<number of beads in the polymer\>              |
    |-sig          |\<size of one bead\>                            |
    |-r            |\<r\> (radius of the sphere)                    |
    
    |Optional flags            |                                                   |
    |-------------------------|---------------------------------------------------|
    |-o \<output\>            |Output file name \[default = out.gro\]              |
    |-bond \<value\>          |Manual bond distance \[default = sigma\]           |
    |-c                       |Center polymer inside box (overrides -centre)      |
    |-centre \<x\> \<y\> \<z\>|Define center \[default (0,0,0)\]                   |
    |-avoid \<true/false\>    |Self avoiding beads \[default true\]               |
    |-nt                      |<number of CPU threads to use> \[default 1\]       |
    |-v                       |Verbose. Print parameters.                         |
    
    Box is set to (2r, 2r, 2r) by default.
   
   
 4. **spcl**
    sph -beads \<integer\> -sig \<float\> -r \<float\> -l \<float\></br>
    |Essential flags|                                                |
    |--------------|------------------------------------------------|
    |-beads        |\<number of beads in the polymer\>              |
    |-sig          |\<size of one bead\>                            |
    |-r            |\<r\> (radius of the sphere)                    |
    |-l            |\<length of cylinder including end-caps\>       |       
    
    |Optional flags            |                                                   |
    |-------------------------|---------------------------------------------------|
    |-o \<output\>            |Output file name \[default = out.gro\]              |
    |-bond \<value\>          |Manual bond distance \[default = sigma\]           |
    |-c                       |Center polymer inside box (overrides -centre)      |
    |-centre \<x\> \<y\> \<z\>|Define center \[default (0,0,0)\]                   |
    |-avoid \<true/false\>    |Self avoiding beads \[default true\]               |
    |-nt                      |<number of CPU threads to use> \[default 1\]       |
    |-v                       |Verbose. Print parameters.                         |
    
    Box is set to (2r, 2r, l) by default.
    
 5. **re** 
    re -f <gro filename>
    
 ### Uninstallation
 1. rm -rf <install location>/polylib
 2. edit .bashrc and remove ```export PATH=$PATH:<install location>/polylib/bin```
 #### exmaple
    rm -rf /home/user/programs/polylib
    edit .bashrc in your home using any text editor and remove the following
    ```export PATH=$PATH:/home/user/programs/polylib/bin```

