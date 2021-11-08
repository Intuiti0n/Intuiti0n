import { Component, OnInit ,Input} from '@angular/core';
import { CookieService } from 'angular2-cookie/services/cookies.service';
import { Router } from '@angular/router';
import {DataService}  from '../data.service';

@Component({
  selector: 'app-continuegame',
  templateUrl: './continuegame.component.html',
  styleUrls: ['./continuegame.component.css']
})
export class ContinuegameComponent implements OnInit {
  message:string;
  username = this._cookieService.get('username').toUpperCase();

  constructor(private router: Router, private _cookieService: CookieService,private data:DataService) {

   }

  ngOnInit() {
    this.data.currentMessage.subscribe(message => this.message = message);
    console.log(this.message);
  }

  onClick(e) {
    e.preventDefault();
    console.log(e);
    this.router.navigate(['story']);
  }

  newMessage(){
    this.data.changeMessage("Hello from sibling");
  }
}
