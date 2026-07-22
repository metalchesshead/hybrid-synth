const board = document.getElementById("board");
const context = board.getContext("2d");
//const rect = board.getBoundingClientRect();
var coords = [];
var xsamp = [];

let isDrawing = false;
let isConnected = false;
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
try {
    if (!isDrawing) return;

    context.lineWidth = "10";
    context.lineCap = "round";
    context.strokeStyle = "#FF0000";

    context.lineTo(e.offsetX, e.offsetY); //prepares a line from the previous point to current mouse position
    context.stroke();    //draw the actual line on the canvas
    context.beginPath(); //resets the current drawing path, prevents lines from connecting unintentionally
    context.moveTo(e.offsetX, e.offsetY); //moves the pen to the new end point
coords.push([Math.round(5000 - 10*(e.offsetY+20))]);
//coords[Math.round(e.offsetX)] = Math.round(5000 - 10*(e.offsetY+20);
//log(e.offsetX);
//document.getElementById("num").innerText = coords.length;
}
catch(error) {
	log('error');
	
}
}

function clearCanvas() {
    context.clearRect(0, 0, board.width, board.height);
	//log("ii");
}

function canvasWidth() {
var board = document.getElementById('board');  
board.width = sampleSize.value;

}

function exportAdjacency() {
/*for (let i=0; i<sampleSize.value; i++){
	if (i>coords.length) {
		xsamp[i] = 1234;
		//xsamp[i] = coords[i];
	
	}
	else {
		//xsamp[i] = coords[i];
		xsamp[i] = 1234;
	}
}
        */

while (coords.length<sampleSize.value) {
	coords.push([0]);
}	
while (coords.length>sampleSize.value) {
	coords.pop(0,-1);
}
/*
            const csvContent = `data:text/csv;charset=utf-8,${coords
                .map((e) => e.join(","))
                .join(", ")}`;
*/
const csvContent = `data:text/csv;charset=utf-8,${coords.map((e) => e.join(",")).join(", ")}`;
  
  const encodedUri = encodeURI(csvContent);
            const link = document.createElement("a");
            link.setAttribute("href", encodedUri);
            link.setAttribute("download", "data.txt");
            document.body.appendChild(link);
            link.click()
        }
		
		
		
		
		
		document.querySelector('#uart-thingy').addEventListener('click', async () => {
			
			while (coords.length<sampleSize.value) {
	coords.push([0]);
}	
while (coords.length>sampleSize.value) {
	coords.pop(0,-1);
}
	//coords.unshift(sampleSize.value);

  // Prompt user to select any serial port.

  const port = await navigator.serial.requestPort();
  //log("heo");
  //  if (isConnected ==false) {
 
  await port.open({ baudRate: 31250 });
  //isConnected= true;
  //}
  const writer = port.writable.getWriter();

const data = new Uint16Array(coords.slice(0,25)); // hello
await writer.write(data);
log(data);
const delay = (ms) => new Promise(resolve => setTimeout(resolve, ms));
await delay(1000);
const data1 = new Uint16Array(coords.slice(25,50)); // hello
await writer.write(data1);
log(data1);

});
/*
function downloadImage() {
    const imageLink = document.createElement("a");
    imageLink.download = `kennyyipcoding-${Date.now()}.png`;  //file name
    imageLink.href = board.toDataURL("image/png");
    imageLink.click();
}
*/
