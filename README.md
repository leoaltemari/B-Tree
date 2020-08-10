# B_Tree_T3 - Search and Insertion
### Description
<p>Implementation of a B-Tree data scruct to indexes a binary file that contais register of births in the country</p>
 
### Files Templates
#### Binary File
  ##### All the register in the binary file has 128 bytes, inluding the header
     The header register follows this template:
   <img src=".github/header.PNG" />
    
     The data register folows this template:
   <img src=".github/data.PNG" />
  The fields in the data register are organized followint this order:
      <p>campo1. sizeof the field cidadeMae (4 bytes) <br>
      campo2. sizeof the field cidadeBebe (4 bytes)<br>
      campo3. cidadeMae (variable size)<br>
      campo4. cidadeBebe (variable size)<br>
      campo5. idNascimento (4 bytes)<br>
      campo6. idadeMae (4 bytes)<br>
      campo7. dataNascimento (10 bytes)<br>
      campo8. sexoBebe (1 byte)<br>
      campo9. estadoMae (2 bytes)<br>
      campo10. estadoBebe (2 bytes)<br></p>
      
 #### B-Tree data structure
  ##### The B-Tree is in a binary file too and was implemented folowing this image below
  <img src=".github/Btree.PNG"  height="400px" width="600px" align="center" />
  
        The difference in the implementation is that the page has 5 keys, and the KEY is a pair key-value, where the key
        is the birthID(field 5 of the binary data file) and the value is the current RRN of the register that contains
        this birthID
  ##### The B-Tree binary file is organized following the .github bellow:
    Header Register:
   <img src=".github/btree_header.PNG" /><br>
    
    Disk Pages:
   <img src=".github/btree_disk_pages.PNG" />
