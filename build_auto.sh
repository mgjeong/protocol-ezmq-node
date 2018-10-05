#!/bin/bash
set +e
#Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"
NO_COLOUR="\033[0m"

PROJECT_ROOT=$(pwd)
DEP_ROOT=$(pwd)/dependencies
EZMQ_TARGET_ARCH="$(uname -m)"
EZMQ_WITH_DEP=false
EZMQ_BUILD_MODE="release"
EZMQ_WITH_SECURITY=true

install_dependencies() {
    if [ -d "./dependencies/protocol-ezmq-cpp" ] ; then
        echo "dependencies folder exist"
    else
        mkdir dependencies
        cd ./dependencies
        #clone ezmq-protocol-cpp
        git clone git@github.sec.samsung.net:RS7-EdgeComputing/protocol-ezmq-cpp.git
        cd $PROJECT_ROOT
    fi

    cd ./dependencies/protocol-ezmq-cpp

    # Build ezmq-protocol-cpp for given architecture [x86/x86_64/armhf]
    echo -e "${GREEN}Installing ezmq library and its dependencies${NO_COLOUR}"
    if [ "armhf" = ${EZMQ_TARGET_ARCH} ]; then
        ./build_auto.sh --with_dependencies=${EZMQ_WITH_DEP} --target_arch=armhf-native --build_mode=${EZMQ_BUILD_MODE} --with_security=${EZMQ_WITH_SECURITY}
    else 
        ./build_auto.sh --with_dependencies=${EZMQ_WITH_DEP} --target_arch=${EZMQ_TARGET_ARCH} --build_mode=${EZMQ_BUILD_MODE} --with_security=${EZMQ_WITH_SECURITY}
    fi
    
    echo -e "${GREEN}Installing node-gyp${NO_COLOUR}"
    npm install node-gyp
    echo -e "${GREEN}Installing NAN${NO_COLOUR}"
    npm install --save nan
    echo -e "${GREEN}Installing jsdoc${NO_COLOUR}"
    npm install --save-dev jsdoc
    echo -e "${GREEN}Installing mocha [unit test]${NO_COLOUR}"
    npm install --save-dev mocha
    echo -e "${GREEN}Installing nyc [Code Coverage]${NO_COLOUR}"
    npm install --save-dev nyc

    echo -e "${GREEN}Installation of ezmq dependencies [protocol-ezmq-cpp] done${NO_COLOUR}"
}

build_x86() {
    cd $PROJECT_ROOT
    node_modules/node-gyp/bin/node-gyp.js clean
    if [ "debug" = ${EZMQ_BUILD_MODE} ]; then
        node_modules/node-gyp/bin/node-gyp.js --config=x86_debug configure
    else
        node_modules/node-gyp/bin/node-gyp.js --config=x86_release configure
    fi
    node_modules/node-gyp/bin/node-gyp.js build
}

build_x86_64() {
    cd $PROJECT_ROOT
    node_modules/node-gyp/bin/node-gyp.js clean
    if [ "debug" = ${EZMQ_BUILD_MODE} ]; then
        node_modules/node-gyp/bin/node-gyp.js --config=x86_64_debug configure
    else
        node_modules/node-gyp/bin/node-gyp.js --config=x86_64_release configure
    fi
    node_modules/node-gyp/bin/node-gyp.js build
}

build_armhf() {
    cd $PROJECT_ROOT
    node_modules/node-gyp/bin/node-gyp.js clean
    if [ "debug" = ${EZMQ_BUILD_MODE} ]; then
        node_modules/node-gyp/bin/node-gyp.js --config=armhf_debug configure
    else
        node_modules/node-gyp/bin/node-gyp.js --config=armhf_release configure
    fi
    node_modules/node-gyp/bin/node-gyp.js build
}

clean_ezmq() {
    echo -e "Cleaning ${BLUE}${PROJECT_ROOT}${NO_COLOUR}"
    echo -e "Deleting  ${RED}${PROJECT_ROOT}/dependencies/${NO_COLOUR}"
    rm -rf ./dependencies/protocol-ezmq-cpp
    echo -e "Finished Cleaning ${BLUE}${EZMQ}${NO_COLOUR}"
}

usage() {
    echo -e "${BLUE}Usage:${NO_COLOUR} ./build_auto.sh <option>"
    echo -e "${GREEN}Options:${NO_COLOUR}"
    echo "  --target_arch=[x86|x86_64|armhf]                                   :  Choose Target Architecture"
    echo "  --with_dependencies=[true|false](default: false)                   :  Build ezmq-node with its dependency protocol-ezmq-cpp"
    echo "  --build_mode=[release|debug](default: release)                     :  Build protocol-ezmq-cpp library in release or debug mode"
    echo "  --with_security=[true|false](default: true)                        :  Build ezmq library with or without Security feature"
    echo "  -c                                                                 :  Clean ezmq Repository and its dependencies"
    echo "  -h / --help                                                        :  Display help and exit"
    echo -e "${GREEN}Notes: ${NO_COLOUR}"
    echo "  - While building newly for any architecture use -with_dependencies=true option."
    echo "  - Before running script, Make sure libsodium is installed, it can be installed using:"
    echo "    $ sudo apt-get install libsodium-dev"
}

build() {
    echo -e "${GREEN}Target Arch is: $EZMQ_TARGET_ARCH${NO_COLOUR}"
    echo -e "${GREEN}Build mode is: $EZMQ_BUILD_MODE${NO_COLOUR}"
    echo -e "${GREEN}Build with depedencies: ${EZMQ_WITH_DEP}${NO_COLOUR}"
    echo -e "${GREEN}Is security enabled: $EZMQ_WITH_SECURITY${NO_COLOUR}"
    if [ ${EZMQ_WITH_DEP} = true ]; then
        install_dependencies
    fi
    if [ "x86" = ${EZMQ_TARGET_ARCH} ]; then
         build_x86;
    elif [ "x86_64" = ${EZMQ_TARGET_ARCH} ]; then
         build_x86_64;
    elif [ "armhf" = ${EZMQ_TARGET_ARCH} ]; then
         build_armhf;
    else
         echo -e "${RED}Not a supported architecture${NO_COLOUR}"
         usage; exit 1;
    fi
    echo -e "${GREEN}Installation of ezmq addon done${NO_COLOUR}"
}

process_cmd_args() {
    if [ "$#" -eq 0  ]; then
        echo -e "No argument.."
        usage; exit 1
    fi

    while [ "$#" -gt 0  ]; do
        case "$1" in
            --with_dependencies=*)
                EZMQ_WITH_DEP="${1#*=}";
                if [ ${EZMQ_WITH_DEP} != true ] && [ ${EZMQ_WITH_DEP} != false ]; then
                    echo -e "${RED}Unknown option for --with_dependencies${NO_COLOUR}"
                    shift 1; exit 0
                fi
                shift 1;
                ;;
            --target_arch=*)
                EZMQ_TARGET_ARCH="${1#*=}";
                shift 1
                ;;
            --build_mode=*)
                EZMQ_BUILD_MODE="${1#*=}";
                shift 1;
                ;;
            --with_security=*)
                EZMQ_WITH_SECURITY="${1#*=}";
                if [ ${EZMQ_WITH_SECURITY} != true ] && [ ${EZMQ_WITH_SECURITY} != false ]; then
                    echo -e "${RED}Unknown option for --with_security${NO_COLOUR}"
                    shift 1; exit 0
                fi              
                shift 1;
                ;;  
            -c)
                clean_ezmq
                shift 1; exit 0
                ;;
            -h)
                usage; exit 0
                ;;
            --help)
                usage; exit 0
                ;;
            -*)
                echo -e "${RED}"
                echo "unknown option: $1" >&2;
                echo -e "${NO_COLOUR}"
                usage; exit 1
                ;;
            *)
                echo -e "${RED}"
                echo "unknown option: $1" >&2;
                echo -e "${NO_COLOUR}"
                usage; exit 1
                ;;
        esac
    done
}

process_cmd_args "$@"
echo -e "Building ezMQ-node library("${EZMQ_TARGET_ARCH}").."
build
echo -e "Done building ezMQ-node library("${EZMQ_TARGET_ARCH}")"

exit 0

