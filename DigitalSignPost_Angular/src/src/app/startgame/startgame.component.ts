import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-startgame',
  templateUrl: './startgame.component.html',
  styleUrls: ['./startgame.component.css']
})
export class StartgameComponent implements OnInit {

  constructor(private router: Router) { }

  ngOnInit() {
  }


  onClick(e) {
    e.preventDefault();
    this.router.navigate(['story']);
  }

  goBack(e) {
    e.preventDefault();
    this.router.navigate(['body']);
  }
}
