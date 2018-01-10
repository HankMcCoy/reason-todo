let str = ReasonReact.stringToElement;

type action =
  | Change(string)
  | Toggle(TodoItem.todo)
  | Add;

type state = {
  newTodo: string,
  todos: array(TodoItem.todo)
};

let component = ReasonReact.reducerComponent("Page");

let updateIn = (updateFn, arr, valToUpdate) => Array.map(
  (curVal) => curVal === valToUpdate
    ? updateFn(curVal)
    : curVal
);

let make = (_children) => {
  ...component,
  initialState: () => {
    newTodo: "",
    todos: [||]
  },
  reducer: (action, state) =>
    switch action {
    | Change(value) => ReasonReact.Update({...state, newTodo: value})
    | Toggle(todoToToggle) => ReasonReact.Update({
      ...state,
      todos: Array.map(
        (curTodo) => curTodo === todoToToggle
          ? TodoItem.{
            text: curTodo.text,
            isChecked: ! curTodo.isChecked
          }
          : curTodo,
        state.todos
      )
    })
    | Add =>
      ReasonReact.Update({
        newTodo: "",
        todos: Array.append(
          [|TodoItem.{ text: state.newTodo, isChecked: false }|],
          state.todos
        )
      })
    },
  render: ({send, state: {newTodo, todos}}) =>
    <div>
      <input
        _type="text"
        onChange={event => {
          let value = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;
          send(Change(value))
        }}
        value=newTodo
      />
      <button onClick={_event => send(Add)}>(str("+"))</button>
      <div>
        (ReasonReact.arrayToElement(
          Array.map((todo) =>
            <TodoItem todo handleToggle={_event => send(Toggle(todo))}/>,
            todos
          )))
      </div>
    </div>
};
