type item = {
    id: int,
    title: string,
    completed: bool
};

type action = 
    | AddItem
    | ToggleItem(int)
    | UpdateNewTitle(string)
    | ToggleCompleted;

type state = {
    newTitle: string,
    items: list(item),
    isCompleted:bool
};
let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;

let component = ReasonReact.reducerComponent("Page1");

let str = ReasonReact.stringToElement;

let lastId = ref(0);
let newItem = (newTitle:string) => {
    lastId := lastId^ + 1;
    {id: lastId^, title:newTitle, completed: false }
};
module TodoItem = {
    let component = ReasonReact.statelessComponent("TodoItem");
    let make = (~item, ~onToggle, _children) => {
        ...component,
        render: (_self) =>
            <div className="item" onClick=((_evt) => onToggle())>
                <input
                    _type="checkbox"
                   checked=(Js.Boolean.to_js_boolean(item.completed))
                   /* TODO make interactive */
                />
                (str(item.title))
            </div>
        };
    };

let make = ( _children) => {
  ...component,
  initialState: () => {
    newTitle: "A new title",
    items: [
        {id: 0, title: "Write somethings to do", completed: false}
    ],
    isCompleted: true,
  },
  reducer: (action, state) =>
    switch action {
    | AddItem => ReasonReact.Update({ ...state, newTitle: "", items: [newItem(state.newTitle), ...state.items]})
    | ToggleItem(id) =>
      let items = List.map(
        (item) =>
          item.id === id ?
            {...item, completed: ! item.completed} : item,
          state.items
        );
      ReasonReact.Update({...state, items: items})
    | UpdateNewTitle(newTitle) => ReasonReact.Update({...state, newTitle:newTitle})
    | ToggleCompleted => ReasonReact.Update({...state, isCompleted: !state.isCompleted})
  },
  render: ({state: {items, newTitle, isCompleted}, reduce}) => {
    let numItems = List.length(items);
    let handleKeyUp = (evt) => { 
        if (ReactEventRe.Keyboard.key(evt) == "Enter" ) {
            (reduce(() => AddItem))()
        }
    };
    <div className="app">
      <div className="title">
        <input 
            value=newTitle
            onChange=(reduce(((evt) => UpdateNewTitle(valueFromEvent(evt)))))
            onKeyUp=(handleKeyUp)
        />
        <button 
            onClick=(reduce((_evt) => AddItem)) 
        >
            (str("Add"))
        </button>
    </div>
    <div>
        <a href="#" onClick=(reduce((_e) => ToggleCompleted))>
            (isCompleted ? str("Show completed") : str("Hide completed"))
        </a>
    </div>
      <div className="items">
        (
            items
              |> List.filter(({completed}) => !isCompleted ? !completed : true )
              |> List.map((item) => <TodoItem
                  key=(string_of_int(item.id))
                  item
                  onToggle=(reduce(() => ToggleItem(item.id))) />) 
              |> Array.of_list 
              |> ReasonReact.arrayToElement 
        )
      </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};

