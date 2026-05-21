const board = document.getElementById("board");
const context = board.getContext("2d");

let isDrawing = false;
const clearButton = document.getElementById("clear-button");

board.addEventListener("pointerdown", () => {isDrawing = true}); //start drawing
board.addEventListener("pointerup", () => { //stop drawing
    isDrawing = false;
    context.beginPath(); //resets the current drawing path, prevents lines from connecting unintentionally
});
board.addEventListener("pointerout", () => {isDrawing = false}); //mouse leaves the canvas, stop drawing
board.addEventListener("pointermove", draw);
board.style.touchAction = "none";



function draw(e) { //e = event, contains mouse click, position, etc information
    if (!isDrawing) return;

    context.lineWidth = brushSize.value;
    context.lineCap = "round";
    context.strokeStyle = colorPicker.value;

    context.lineTo(e.offsetX, e.offsetY); //prepares a line from the previous point to current mouse position
    context.stroke();    //draw the actual line on the canvas
    context.beginPath(); //resets the current drawing path, prevents lines from connecting unintentionally
    context.moveTo(e.offsetX, e.offsetY); //moves the pen to the new end point
}

function clearCanvas() {
    context.clearRect(0, 0, board.width, board.height);
}

function fillCanvas() {
    context.fillStyle = colorPicker.value;
    context.fillRect(0, 0, board.width, board.height);
}
