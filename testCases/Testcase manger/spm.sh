
    #!/bin/bash
    # A sample Bash script, by Ryan
    #echo Hello World!
    #echo "I'm in $(pwd)"
    cd ..
    cd ..
    echo "hi enter the file that you want"
    read filez
    make
    ./csc testCases/$filez
    cd sam_folder
    if [ -f $filez.asm ]; then
       rm $filez.asm
       rm $filez.lis
       echo "removing old test case"
      fi
    cd ..
    cd testCases
    if [ -f $filez.asm ]; then
    cp $filez.asm ../sam_folder
    echo "copying file to folder"
    fi
    cd ../sam_folder
    make
    ./sam $filez
    ./macc $filez

    #cp $filez.asm ../sam_folder/
