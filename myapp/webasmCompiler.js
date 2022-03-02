const fs = require('fs');
const { execSync } = require("child_process");

const codeDir = './webasm-config/src';

function createCppFile(code){
    const codeFile = `${codeDir}/code.cpp`;
    if (!fs.existsSync(codeDir)){
        console.log("creating dir");
        fs.mkdirSync(codeDir);
    }
    var file = fs.openSync(codeFile, 'w');
    fs.writeSync(file, code);
    fs.close(file);
    return codeFile;
}

function prepareArduinoSource(source){
    var resultSource = `#include "Arduino.h"\n`;
    resultSource += source;
    return resultSource;
}

//ref https://depth-first.com/articles/2019/10/16/compiling-c-to-webassembly-and-running-it-without-emscripten/
function compileCppSource(source){
    const preprocessed = prepareArduinoSource(source);
    const fileLocation = createCppFile(preprocessed);
    const makefileLocation = `webasm-config`

    execSync(`make -C ${makefileLocation} clean`, (error, stdout, stderr) => {
        if (error) {
            console.log(`error: ${error.message}`);
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
        }
        console.log(`stdout: ${stdout}`);
    });

    execSync(`make -C ${makefileLocation}`, (error, stdout, stderr) => {
        if (error) {
            console.log(`error: ${error.message}`);
            return;
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
            return;
        }
        console.log(`stdout: ${stdout}`);
    });
    execSync(`rm -f public/*`, (error, stdout, stderr) => {
        if (error) {
            console.log(`error: ${error.message}`);
        }
        else if (stderr) {
            console.log(`stderr: ${stderr}`);
        }
        console.log(`stdout: ${stdout}`);
    });
    execSync(`cp ${makefileLocation}/bin/exec.wasm public/`);
    execSync(`cp ${makefileLocation}/bin/exec.js public/`);
    
    //maybe use some user dir to handle this, even if its temp
    return {jsfile : 'exec.js', wasmfile: 'exec.wasm'};

    //versao antiga
    //const data = fs.readFileSync(`${makefileLocation}/bin/exec.wasm`);
}



module.exports = {
    compileCppSource : compileCppSource
};