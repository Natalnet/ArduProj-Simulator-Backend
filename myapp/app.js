const util = require('util')
const express = require('express')
const cors = require("cors");
const { execSync } = require("child_process");

const webAsmCompile = require('./webasmCompiler.js')

const corsOptions ={
   origin:'*', 
   credentials:true,            //access-control-allow-credentials:true
   optionSuccessStatus:200,
}


const app = express()
const port = 3001
app.use(cors(corsOptions))
app.use(express.json())
app.use(express.static('./public'));

app.get('/');
app.post('/compile-wasm', (req, res) => {
    console.log(`Received code ${util.inspect(req.body)}`)
    compiledCode = webAsmCompile.compileCppSource(req.body.code);
    res.setHeader('Content-Type', 'application/octet-stream');

    res.send({res : compiledCode})
})

try {
  execSync(`em++ --version`);
}
catch(e){
  console.log(`Error calling em++, the backend needs this command to execute properly, exiting`);
  process.exit(-1)
}

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})

