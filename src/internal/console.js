var console = {};
console.log = function() {
	print(__util.format.apply(null, arguments));
}
