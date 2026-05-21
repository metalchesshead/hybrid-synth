const board = document.getElementById("board")'
const context = board.getContext("2d");

//const brushSize = document.getElementById("brush-size");
const clearButton = document.getElementById("clear-button");

board.addEventListener("mousemove", draw);

function draw() {
  context.lineWidth = 10px;
  context.lineCap = "round";
  context.strokeStyle = colorPicker.value;

  context.lineTo(e.offsetX, e.offsetY);
  context.stroke();
  context.beginPath();
  context.moveTo(e.offsetX, e.offsetY);
    }
