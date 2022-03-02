/*por algum motivo, quando usamos uma função para guardar o ambiente de execução
  o destino do arquivo wasm é perdido (antes apontava pra o backend, passa a apontar para o front)
  acho que daria para pensar em algum workaround usando o env*/
Module['locateFile'] = (path, scriptDirectory) =>{
    return 'http://localhost:3001/' + path;
}
