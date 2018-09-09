class Person {
	constructor(private _name: string, private _age: number) {
	}
	get name(): string {
		return this._name;
	}
	get age(): number {
		return this._age;
	}
}
let people = [
	new Person('Bob', 33),
	new Person('Susan', 24),
	new Person('Jimmy', 8)
];
for (let person of people) {
	print(person.name + ' is ' + person.age + ' years old');
}
