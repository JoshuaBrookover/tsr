let i = 5;
console.log(i);
let timer = setInterval(() => {
	console.log(--i);
	if (i == 0) {
		clearInterval(timer);
	}
}, 1000);
