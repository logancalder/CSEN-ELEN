import React from "react";
import { BrowserRouter as Router, Routes, Route, Link } from "react-router-dom";
import "./App.css";
import Help from "./Help";
import Faq from "./Faq";
import Info from "./Info";
import Ideas from "./Ideas";

function App() {
  return (
    <Router>
      <div className="App">
        <Routes>
          <Route path="/" element={<h1>Welcome to My App</h1>} />
          <Route path="/faq" element={<Faq />} />
          <Route path="/help" element={<Help />} />
          <Route path="/info" element={<Info />} />
          <Route path="/ideas" element={<Ideas />} />
        </Routes>
      </div>
    </Router>
  );
}

export default App;
