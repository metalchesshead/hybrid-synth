const board = document.getElementById("board");
const context = board.getContext("2d");

var coords = [];

let isDrawing = false;
const clearButton = document.getElementById("clear-button");
const downloadButton = document.getElementById("download-button");
var sampleSize = document.getElementById("samples");
const enterButton = document.getElementById("enter-button");

board.addEventListener("pointerdown", () => {isDrawing = true}); //start drawing
board.addEventListener("pointerup", () => { //stop drawing
    isDrawing = false;
    context.beginPath(); //resets the current drawing path, prevents lines from connecting unintentionally
});
board.addEventListener("pointerout", () => {isDrawing = false}); //mouse leaves the canvas, stop drawing
board.addEventListener("pointermove", draw);
board.style.touchAction = "none";

clearButton.addEventListener("click", clearCanvas);
downloadButton.addEventListener("click", exportAdjacency);
enterButton.addEventListener("click", canvasWidth); 



function draw(e) { //e = event, contains mouse click, position, etc information
    if (!isDrawing) return;

    context.lineWidth = "10";
    context.lineCap = "round";
    context.strokeStyle = "#FF0000";

    context.lineTo(e.offsetX, e.offsetY); //prepares a line from the previous point to current mouse position
    context.stroke();    //draw the actual line on the canvas
    context.beginPath(); //resets the current drawing path, prevents lines from connecting unintentionally
    context.moveTo(e.offsetX, e.offsetY); //moves the pen to the new end point
coords.push([Math.round(5000 - 10*(e.offsetY+20))])

document.getElementById("num").innerText = coords.length;
}

function clearCanvas() {
    context.clearRect(0, 0, board.width, board.height);
	log("ii");
}

function canvasWidth() {
var board = document.getElementById('board');  
board.width = sampleSize.value;
}

function exportAdjacency() {

            


            const csvContent = `data:text/csv;charset=utf-8,${coords
                .map((e) => e.join(","))
                .join(", ")}`;
            const encodedUri = encodeURI(csvContent);
            const link = document.createElement("a");
            link.setAttribute("href", encodedUri);
            link.setAttribute("download", "data.txt");
            document.body.appendChild(link);
            link.click()


        }
		document.querySelector('#uart-thingy').addEventListener('click', async () => {
  // Prompt user to select any serial port.
  const port = await navigator.serial.requestPort();
  //log("heo");
  await port.open({ baudRate: 31250 });
  const writer = port.writable.getWriter();

const data = new Uint8Array(coords); // hello
await writer.write(data);

});
/*
function downloadImage() {
    const imageLink = document.createElement("a");
    imageLink.download = `kennyyipcoding-${Date.now()}.png`;  //file name
    imageLink.href = board.toDataURL("image/png");
    imageLink.click();
}
*/
