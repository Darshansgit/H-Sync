const firebaseConfig = {

  apiKey: "AIzaSyA6X7xLIIT0wPb8eMvGS2NIiLsmYrkiJ0M",

    authDomain: "esp2fb-ff2ff.firebaseapp.com",

      databaseURL: "https://esp2fb-ff2ff-default-rtdb.asia-southeast1.firebasedatabase.app",

        projectId: "esp2fb-ff2ff",

        storageBucket: "esp2fb-ff2ff.appspot.com",

          messagingSenderId: "70696485797",

            appId: "1:70696485797:web:63486f6028ea8822b69e4c"

}

async function loadModel()
{
   return tf.loadLayersModel('/finalModel/model.json');
   
}

async function preprocessing_data()
{
  console.clear();
  input_data = document.getElementById('textarea').value

    //taking the string, replacing the "," with ' ', just changing the delimiter 
    input_data = input_data.replace(',', ' ');
    input_data = input_data.replace(',', ' ');
    input_data = input_data.replace(',', ' ');
    input_data = input_data.replace(',', ' ');
    input_data = input_data.replace(',', ' ');

      //now taking the input and splitting it into segments and returning an array of strings
      split_input = input_data.split(' ');

        // changing the string array into a number array
        let i = 0;

          while (i < split_input.length) 
          {
              split_input[i] = Number(split_input[i]);
              i++;
          }
          console.log(split_input);
  // return split_input;
// split_input is the final input array to be passed
}

async function button() {
  const model = await loadModel();
// fetching the data from container
    const input = await preprocessing_data();

      let result = model.predict(tf.tensor2d(split_input, [1, 6])).dataSync();

        output = tf.argMax(result).dataSync();
        output = Number(output)+1;
        console.log(output);
}


function fetch_FB_data()
{

}