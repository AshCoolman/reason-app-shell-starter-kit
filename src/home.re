let component = ReasonReact.statelessComponent("Home");

let make = _children => {
  ...component,
  render: _self => {
    let x = 3 + 2;
    let square = x * x;
    <div className="Home"> (
    ReasonReact.stringToElement(string_of_int(square))
    )</div>
  }
};
