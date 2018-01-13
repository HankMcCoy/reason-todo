let str = ReasonReact.stringToElement;
let to_js_bool = Js.Boolean.to_js_boolean;

type viewMode =
  | All
  | Complete
  | Incomplete;

type action =
  | Change(string)
  | Toggle(TodoItem.todo)
  | SetViewMode(viewMode)
  | Add;

type state = {
  newTodo: string,
  viewMode: viewMode,
  todos: list(TodoItem.todo)
};

let component = ReasonReact.reducerComponent("Page");

let updateIn = (valToUpdate, newVal, arr) => List.map(
  (curVal) => curVal === valToUpdate
    ? newVal
    : curVal,
  arr
);

let make = (_children) => {
  ...component,
  initialState: () => {
    newTodo: "",
    viewMode: All,
    todos: []
  },
  reducer: (action, state) =>
    switch action {
    | Change(value) => ReasonReact.Update({...state, newTodo: value})
    | Toggle(todoToToggle) => ReasonReact.Update({
      ...state,
      todos: updateIn(
        todoToToggle,
        TodoItem.{
          ...todoToToggle,
          isChecked: ! todoToToggle.isChecked
        },
        state.todos
      )
    })
    | SetViewMode(viewMode) => ReasonReact.Update({...state, viewMode})
    | Add =>
      ReasonReact.Update({
        ...state,
        newTodo: "",
        todos: [TodoItem.{ text: state.newTodo, isChecked: false }] @ state.todos
      })
    },
  render: ({send, state: {newTodo, todos, viewMode}}) =>
    <div>
      <form onSubmit={(event) => { ReactEventRe.Form.preventDefault(event) }}>
        <input
          _type="text"
          onChange={event => {
            let value = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;
            send(Change(value))
          }}
          value=newTodo
        />
        <button onClick={_event => send(Add)}>(str("+"))</button>
      </form>
      <div>
        (todos
          /* Filter to match the view mode */
          |> List.filter((todo: TodoItem.todo) =>
            switch (viewMode) {
            | All => true
            | Complete => todo.isChecked
            | Incomplete => ! todo.isChecked
            })
          |> List.map((todo) =>
            <TodoItem todo handleToggle={_event => send(Toggle(todo))}/>)
          |> Array.of_list
          |> ReasonReact.arrayToElement)
      </div>
      <div>
        <label>
          <input
            _type="radio"
            name="viewMode"
            checked={to_js_bool(viewMode === All)}
            onChange={(_event) => send(SetViewMode(All))}
          />
          (str("All"))
        </label>
        <label>
          <input
            _type="radio"
            name="viewMode"
            checked={to_js_bool(viewMode === Complete)}
            onChange={(_event) => send(SetViewMode(Complete))}
          />
          (str("Complete"))
        </label>
        <label>
          <input
            _type="radio"
            name="viewMode"
            checked={to_js_bool(viewMode === Incomplete)}
            onChange={(_event) => send(SetViewMode(Incomplete))}
          />
          (str("Incomplete"))
        </label>
      </div>
    </div>
};
