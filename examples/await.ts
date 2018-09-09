(async() => {
	console.log(5);
	for (let i = 4; i >= 0; --i) {
		await new Promise(resolve => setTimeout(resolve, 1000));
		console.log(i);
	}
})();
