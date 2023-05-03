
async function loadModel()
{
   return tf.loadLayersModel('/tfjsmodel/model.json');
}
async function preprocessing_data()
{
  console.clear();
  input_data = document.getElementById('textarea').value

  //taking the string, replacing the "," with ' ', just changing the delimiter 
  input_data = input_data.replace(',', ' ');
  input_data= input_data.replace(',', ' ');

  //now taking the input and splitting it into segments and returning an array of strings
  split_input = input_data.split(' ');

  // changing the string array into a number array
  let i = 0;

  while (i < split_input.length) 
  {
      split_input[i] = Number(split_input[i]);
      i++;
  }
  return split_input;
// split_input is the final input array to be passed

}

async function button() {
const model = await loadModel();
// fetching the data from container
const input = await preprocessing_data();

let result = model.predict(tf.tensor2d(split_input, [1, 3])).dataSync();

output = tf.argMax(result).dataSync();
output = Number(output)+1;
if (output ==1)
{
  document.write("hypotension");
}

}


  