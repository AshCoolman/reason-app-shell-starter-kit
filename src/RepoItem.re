let component = ReasonReact.statelessComponent("RepoItem");
let strToEl = ReasonReact.stringToElement;
let strInt = string_of_int;
let make = (~repo: RepoData.repo, _children) => {
    ...component,
    render: (_self) =>
        <div className="RepoItem">
            <a href=repo.html_url>
                <h2>{ReasonReact.stringToElement(repo.full_name)}</h2>
            </a>
            {strToEl(strInt(repo.stargazers_count) ++ " stars")}
        </div>

};
