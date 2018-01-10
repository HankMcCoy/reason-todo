let str = ReasonReact.stringToElement;
let component = ReasonReact.statelessComponent("TodoItem");

type todo = {
  text: string,
  isChecked: bool
};

let make = (~todo, ~handleToggle, _children) => {
  ...component,
  render: _self => {
    <div>
      (str(todo.text))
      <input
        _type="checkbox"
        checked=(Js.Boolean.to_js_boolean(todo.isChecked))
        onChange={handleToggle}
      />
    </div>
  }
}
