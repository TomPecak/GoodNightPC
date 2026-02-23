const { invoke } = window.__TAURI__.core;
const { listen } = window.__TAURI__.event;

let minutesInput;
let startBtn;
let greetInputEl;
let greetMsgEl;

async function startTimer() {
  console.log("Starting timer...");
  const minutes = parseInt(minutesInput.value, 10);
  if (isNaN(minutes) || minutes <= 0) return;

  const seconds = minutes * 60;

  console.log(`Setting idle timer for ${seconds} seconds...`);

  //call rust 
  await invoke("start_timer", { seconds: seconds });
  console.log("After invoking rust start_timer");


}

async function greet() {
  // Learn more about Tauri commands at https://tauri.app/develop/calling-rust/
  greetMsgEl.textContent = await invoke("greet", { name: greetInputEl.value });
}

window.addEventListener("DOMContentLoaded", () => {
  minutesInput = document.querySelector("#minutes-input");
  startBtn = document.querySelector("#start-btn");

  greetInputEl = document.querySelector("#greet-input");
  greetMsgEl = document.querySelector("#greet-msg");
  document.querySelector("#greet-form").addEventListener("submit", (e) => {
    e.preventDefault();
    greet();
  });

  startBtn.addEventListener("click", startTimer);
});
