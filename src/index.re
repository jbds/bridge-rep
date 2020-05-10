open Reprocessing;

// minimalist demo
// let setup = (env) => Env.size(~width=600, ~height=600, env);
// let draw = (_state, env) => {
//   Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
//   Draw.fill(Utils.color(~r=41, ~g=166, ~b=244, ~a=255), env);
//   Draw.rect(~pos=(150, 150), ~width=300, ~height=300, env)
// };
// run(~setup, ~draw, ());

// bind to js global window size variables
[@bs.val] external iW: int = "innerWidth";
[@bs.val] external iH: int = "innerHeight";

// sync canvas size to window size
let envWidthDivWindowWidth = 0.7;
let windowToEnvWidth = (w) => int_of_float(float_of_int(w) *. envWidthDivWindowWidth);
let windowToEnvHeight = (h) => h;

type stateT = {
  image: imageT,
  cardTableImage: imageT,
  cardCount: int
}


let setup = (env) => {
  Env.size(
    ~width=windowToEnvWidth(iW), 
    ~height=windowToEnvHeight(iH), 
    env
  );
  {
    cardTableImage: Draw.loadImage(~filename="assets/green_baize.jpg", ~isPixel=true, env),
    image: Draw.loadImage(~filename="assets/JC.svg", ~isPixel=true, env),
    cardCount: 0
  }
}

let draw = (state, env) => {
  let envW = windowToEnvWidth(iW);
  let envH = windowToEnvHeight(iH);
  Env.size(~width=envW, ~height=envH, env);
  Draw.image(state.cardTableImage, ~pos=(0,0), ~width=envW, ~height=envH, env);
  {
    ...state,
    //windowH: state.windowH +. (60. *. Env.deltaTime(env))
    cardCount: state.cardCount + 1
  }
}

let () = run(~setup, ~draw, ());
