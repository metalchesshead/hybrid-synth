const board = document.getElementById("board");
const context = board.getContext("2d");
//const rect = board.getBoundingClientRect();
var coords = [];
var xsamp = [];
var goodcor = [];
var temparrayx = [];
var temparrayy = [];

let isDrawing = false;
let isConnected = false;
const clearButton = document.getElementById("clear-button");
const downloadButton = document.getElementById("download-button");
var sampleSize = document.getElementById("samples");
const enterButton = document.getElementById("enter-button");
const uploadButton = document.getElementById("uploadlut");
var lutInput = document.getElementById("lut-input");


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
uploadButton.addEventListener("click", uploadLut);
function interpolateArray(data, fitCount) {

    var linearInterpolate = function (before, after, atPoint) {
        return before + (after - before) * atPoint;
    };

    var newData = new Array();
    var springFactor = new Number((data.length - 1) / (fitCount - 1));
    newData[0] = data[0]; // for new allocation
    for ( var i = 1; i < fitCount - 1; i++) {
        var tmp = i * springFactor;
        var before = new Number(Math.floor(tmp)).toFixed();
        var after = new Number(Math.ceil(tmp)).toFixed();
        var atPoint = tmp - before;
        newData[i] = linearInterpolate(data[before], data[after], atPoint);
    }
    newData[fitCount - 1] = data[data.length - 1]; // for new allocation
    return newData;
};
	
function uploadLut() {
	

	
	const lutString = lutInput.value;
	log(lutString);
	for (let i=0; i<xsamp.length; i++) {
		

goodcor[i] = Math.trunc(xsamp[i])
	log(goodcor[i]);
	
}
const newarrsize = goodcor[goodcor.length - 1] - goodcor[0];
log(newarrsize);
//temparrayx = interpolateArray(xsamp,sampleSize.value);
temparrayy = interpolateArray(coords,sampleSize.value);
for (let i=0; i<sampleSize.value; i++) {
	//temparrayx[i] = Math.trunc(temparrayx[i]);
	temparrayy[i] = Math.trunc(temparrayy[i]);

	log(temparrayy[i]);
	
}





}

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
coords.push(Math.trunc(5000 - 10*(e.offsetY+20)));
xsamp.push(e.offsetX);
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

	for (let i=0; i<xsamp.length; i++) {
		

goodcor[i] = Math.trunc(xsamp[i])
	//log(goodcor[i]);
	
}
const newarrsize = goodcor[goodcor.length - 1] - goodcor[0];
//temparrayx = interpolateArray(xsamp,sampleSize.value);
temparrayy = interpolateArray(coords,sampleSize.value);
for (let i=0; i<sampleSize.value; i++) {
	//temparrayx[i] = Math.trunc(temparrayx[i]);
	temparrayy[i] = [Math.trunc(temparrayy[i])];

	//log(temparrayy[i]);
	
}

while (temparrayy.length<sampleSize.value) {
	temparrayy.push([0]);
}	
while (temparrayy.length>sampleSize.value) {
	temparrayy.pop(0,-1);
}

const csvContent = `data:text/csv;charset=utf-8,${temparrayy.map((e) => e.join(",")).join(", ")}`;
  log(newarrsize);

  const encodedUri = encodeURI(csvContent);
            const link = document.createElement("a");
            link.setAttribute("href", encodedUri);
            link.setAttribute("download", "data.txt");
            document.body.appendChild(link);
            link.click()
        }
		
		
		
		
		
		
		
		document.querySelector('#uart-thingy').addEventListener('click', async () => {
			
			
			
	for (let i=0; i<xsamp.length; i++) {
		

goodcor[i] = Math.trunc(xsamp[i])
	//log(goodcor[i]);
	
}
const newarrsize = goodcor[goodcor.length - 1] - goodcor[0];
//temparrayx = interpolateArray(xsamp,sampleSize.value);
temparrayy = interpolateArray(coords,sampleSize.value);
for (let i=0; i<sampleSize.value; i++) {
	//temparrayx[i] = Math.trunc(temparrayx[i]);
	temparrayy[i] = [Math.trunc(temparrayy[i])];

	//log(temparrayy[i]);
	
}

while (temparrayy.length<sampleSize.value) {
	temparrayy.push([0]);
}	
while (temparrayy.length>sampleSize.value) {
	temparrayy.pop(0,-1);
}


  // Prompt user to select any serial port.

  const port = await navigator.serial.requestPort();
  //log("heo");
  //  if (isConnected ==false) {
 
  await port.open({ baudRate: 31250 });
  //isConnected= true;
  //}
  const writer = port.writable.getWriter();
const delay = (ms) => new Promise(resolve => setTimeout(resolve, ms));
var slicetemp = 0;
const j = 0;
delay(1000);
for (let j=0; j<32; j++) {
	// if (temparrayy.length - slicetemp <25) {
		// var data = new Uint16Array(temparrayy.slice(slicetemp,(temparrayy.length))); // hello
	// }
	// else {
	// var data = new Uint16Array(temparrayy.slice(slicetemp,(slicetemp + 25))); // hello
	// }
		var data = new Uint16Array(temparrayy.slice(slicetemp,(slicetemp + 32))); // hello
delay(1000);

await writer.write(data);
log(data);
slicetemp = slicetemp + 32;
}

// await delay(1000);
// const data1 = new Uint16Array(temparrayy.slice(25,50)); // hello
// await writer.write(data1);
// log(data1);
// await delay(1000);
// const data2 = new Uint16Array(temparrayy.slice(50,75)); // hello
// await writer.write(data2);
// log(data2);
// await delay(1000);
// const data3 = new Uint16Array(temparrayy.slice(75,100)); // hello
// await writer.write(data3);

// log(data3);

});
/*
function downloadImage() {
    const imageLink = document.createElement("a");
    imageLink.download = `kennyyipcoding-${Date.now()}.png`;  //file name
    imageLink.href = board.toDataURL("image/png");
    imageLink.click();
}
*/
