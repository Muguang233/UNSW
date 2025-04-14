/**
 * Compute the sum of the integer array.
 * If the array is empty, the sum is 0.
 *
 * @param {Array<number>} array of integers
 * @returns {number} the sum of the array
 */
function arraySum(array) {
  let sum = 0;
  for(let i = 0; i < array.length; i++){
    sum += array[i];
  }
  return sum;
}

/**
 * Compute the product of the given integer array.
 * If the array is empty, the product is 1.
 *
 * @param {Array<number>} array of integers
 * @returns {number} the product of the array
 */
function arrayProduct(array) {
  let pro = 1;
  for(let i = 0; i < array.length; i++){
    pro *= array[i];
  }
  return pro;
}

/**
 * Find the smallest number in the array
 *
 * @param {Array<number>} array of integers
 * @returns {number|null} the smallest number in the array, or
 * null if the array is empty
 */
function arrayMin(array) {
  let min = array[0];
  for(let i = 0; i < array.length; i++){
    if(array[i] < min){
      min = array[i];
    }
  }
  return min;
}

/**
 * Find the largest number in the array
 *
 * @param {Array<number>} array of integers
 * @returns {number|null} the largest number in the array, or
 * null if the array is empty
 */
function arrayMax(array) {
  let max = 0;
  for(let i = 0; i < array.length; i++){
    if(array[i]>max){
      max = array[i];
    }
  }
  return max;
}

/**
 * Determine if the array contains a particular element.
 *
 * @param {Array<number>} array of integers
 * @param {number} item integer to check
 * @returns {boolean} whether the integer item is in the given array
 */
function arrayContains(array, item) {
  if(array.includes(item)){
    return true;
  } else{
    return false;
  }
}

/**
 * Create an array that is the reversed of the original.
 *
 * WARNING: a reminder that the original(s) array must not be modified.
 * You can create new arrays if needed.
 *
 * @param {Array<number>} array of integers
 * @returns {Array<number>} a new reversed array
 */
function arrayReversed(array) {
  const reverse = [];
  for(let i = array.length -1; i>= 0; i--){
    reverse.push(array[i]);
  }
  return reverse;
}

/**
 * Returns the array with all odd numbers removed
 * 
 * WARNING: a reminder that the original(s) array must not be modified.
 * You can create new arrays if needed.
 * 
 * @param {Array<number>} array of integeres
 * @returns {Array<number>} array of integers with odd numbers removed
 */
function removeOdd(array) {
  const even = [];
  for(let i = 0; i < array.length; i++){
    if(array[i]%2 == 0){
      even.push(array[i]);
    }
  }
  return even;
}

/**
 * Returns the array with all the elements floored
 * (rounded down to the nearest integer)
 *
 * WARNING: a reminder that the original(s) array must not be modified.
 * You can create new arrays if needed.
 * 
 * @param {Array<number>} array of numbers
 * @returns {Array<number>} array of integers
 */
function floorArray(array) {
  const floor = [];
  for(let i = 0; i < array.length; i++){
    floor.push(Math.floor(array[i]));
  }
  return floor;
}

/**
 * Given two arrays, multiply the elements at each index from arrays and store
 * the result in a third array. If the given two arrays differ in length,
 * excess elements of the larger array will be added on at the end.
 *
 * For example,
 *     [1, 3, 2]
 *   x [2, 4, 3, 5, 9]
 *   -----------------
 *   = [2, 12, 6, 5, 9]
 *
 * The result will be the same if array1 and array2 are swapped.
 *
 * @param {Array<number>} array1 of integers
 * @param {Array<number>} array2 of integers
 * @returns {Array<number>} array1 x array2 at each index
 */
function arraysMultiply(array1, array2) {
  const Mult = [];
  let arr1 = array1.length;
  let arr2 = array2.length;
  let min = Math.min(arr1,arr2);
  for(let i = 0; i < Math.max(arr1,arr2); i++){
    if(i>min){
      if(arr1>arr2){
        Mult.push(array1[i]);
      }else {
        Mult.push(array2[i]);
      }
    } else {
      Mult.push(array1[i]*array2[i]);
    }
  }
  return Mult;
}

/**
 * Create a third array containing common elements between two arrays.
 *
 * Each element in the first array can map to at most one element
 * in the second array, and vice versa (one-to-one relationship).
 * 
 * Duplicated elements in each array are treated as separate entities.
 *
 * The order is determined by the first array.
 *
 * A few examples,
 *   arraysCommon([1,1], [1,1,1]) gives [1,1]
 *   arraysCommon([1,1,1], [1,1]) gives [1,1]
 *   arraysCommon([1,2,3,2,1], [5,4,3,2,1]) gives [1,2,3]
 *   arraysCommon([1,2,3,2,1], [2,2,3,3,4]) gives [2,3,2]
 *   arraysCommon([1,4,1,1,5,9,2,7], [1,8,2,5,1]) gives [1,1,5,2]
 *
 * WARNING: a reminder that the original array(s) must not be modified.
 * You can create new arrays if needed.
 *
 * @param {Array<number>} array1 of integers
 * @param {Array<number>} array2 of integers
 * @returns {Array<number>} number of common elements between two arrays
 */
function arraysCommon(array1, array2) {
  const copy = array2;
  const com = [];
  for(let i = 0; i < array1.length; i++){
    const index = copy.indexOf(array1[i]);
    if(index != -1) {
      com.push(array1[i]);
      copy.splice(index, 1);
    }
  }
  return com;
}

// ========================================================================= //

/**
 * Debugging code
 */

console.assert(arraySum([1, 2, 3, 4]) === 10, 'arraySum([1,2,3,4]) === 10');
console.assert(arrayProduct([1, 2, 3, 4]) === 24, 'arrayProduct([1,2,3,4]) === 24');

console.log(`
  NOTE: you can't directly compare two arrays with '===', so you may need
  to come up with your own way of comparing arrays this week. For example, you
  could use console.log() and observe the output manually.
`)
console.log();
console.log('Testing : arrayCommon([1,2,3,2,1], [2,2,3,3,4])');
console.log('Received:', arraysCommon([1, 2, 3, 2, 1], [2, 2, 3, 3, 4]));
console.log('Expected: [ 2, 3, 2 ]');
console.log();

// TODO: your own debugging here

console.log('========================================================')

console.log(`
  NOTE: these console.log messages will have no effect
  on automarking, so you do not need to remove before
  submitting your work.
`)