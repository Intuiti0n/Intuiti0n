import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-noid',
  templateUrl: './noid.component.html',
  styleUrls: ['./noid.component.css']
})
export class NoidComponent implements OnInit {

  constructor() { }

  ngOnInit() {
    window.alert("sometext");
  }

  
}
