function charCodeAt(str) {
    return str.charCodeAt(0)
}

function get_gameboard_buffer(gameboard) {
    for (let i=0; i<gameboard.length; i++) {
        gameboard[i] = charCodeAt(gameboard[i])
    }

    let buffer, result;

    var typed_gameboard = new Int32Array(gameboard.length);
    for (let i=0; i<gameboard.length; i++) {
        typed_gameboard[i] = gameboard[i]
    }

    buffer = Module._malloc(typed_gameboard.length * typed_gameboard.BYTES_PER_ELEMENT)
    Module.HEAPF32.set(typed_gameboard, buffer >> 2)
    return buffer;    
}

function get_score(gameboard) {
    let buffer = get_gameboard_buffer(gameboard)
    result = Module.ccall("get_score", null, ["number", "number"], [buffer, gameboard.length])
    return result;    
}

function is_game_over(gameboard) {
    let buffer = get_gameboard_buffer(gameboard)
    result = Module.ccall("is_game_over", null, ["number", "number"], [buffer, gameboard.length])
    return result;    
}

function get_next_move(gameboard){
    let buffer = get_gameboard_buffer(gameboard)
    result = Module.ccall("get_next_move", null, ["number", "number"], [buffer, gameboard.length])
    return result;
}