let i = 5;
print(i);
let timer = setInterval(() => {
	print(--i);
	if (i == 0) {
		clearInterval(timer);
	}
}, 1000);
