var rs = require('readline-sync');

var num1 = rs.question('1st Number: ');
var num2 = rs.question('2nd Number: ');
var num3 = rs.question('3rd Number: ');
var num4 = rs.question('4th Number: ');

function getFactorial(x) {
    var fact = 1;
    for (i = x; i > 0; i--) {
        fact = fact * i;
    }
    return fact;
}
var result1 = getFactorial(num1);

function getSum(x) {
    var arr = x.split('');
    var sum = 0;
    for(i = 0; i < arr.length; i++) {
        var num = Number(arr[i]);
        sum += num;
    }
    return sum;
}
var result2 = getSum(num2);

function getReverse(x) {
    var arr = x.split('');
    var reverse = '';
    for(i = arr.length - 1; i >= 0; i--) {
        reverse += arr[i];
    }
    return reverse;
}
var result3 = getReverse(num3);

function isPalindrome(x) {
    var rev = getReverse(x);
    return x === rev;
}
var result4 = isPalindrome(num4);

console.log("The factorial of the first number is:", result1);
console.log("The sum of all the digits of the second number is:", result2);
console.log("The reverse of the third number is:", result3);
console.log("Is the fourth number a palindrome? (true/false):", result4);