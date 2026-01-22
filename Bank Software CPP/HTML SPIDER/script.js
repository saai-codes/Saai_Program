const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

let mouseX = canvas.width / 2;
let mouseY = canvas.height / 2;

// Track mouse movement
window.addEventListener("mousemove", function (event) {
    mouseX = event.clientX;
    mouseY = event.clientY;
});

// Draw spider
function drawSpider(x, y) {
    ctx.strokeStyle = "white";
    ctx.lineWidth = 1;

    // Spider body
    ctx.beginPath();
    ctx.arc(x, y, 5, 0, Math.PI * 2);
    ctx.stroke();

    // Spider legs
    for (let i = 0; i < 8; i++) {
        let angle = (Math.PI / 4) * i;
        let legX = x + Math.cos(angle) * 15;
        let legY = y + Math.sin(angle) * 15;

        ctx.beginPath();
        ctx.moveTo(x, y);
        ctx.lineTo(legX, legY);
        ctx.stroke();
    }
}

// Animation loop
function animate() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawSpider(mouseX, mouseY);
    requestAnimationFrame(animate);
}

animate();