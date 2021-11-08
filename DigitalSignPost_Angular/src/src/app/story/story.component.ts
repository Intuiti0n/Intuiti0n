import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import {DataService}  from '../data.service';
import { parse } from 'url';

@Component({
  selector: 'app-story',
  templateUrl: './story.component.html',
  styleUrls: ['./story.component.css']
})
export class StoryComponent implements OnInit {
  person = "pedro";
  id_router : number;
  email;
  message:string;

  constructor(private router: Router,private data:DataService) { }

  ngOnInit() {
    this.data.currentMessage.subscribe(message => this.message = message);
    this.id_router= parseInt(this.message);
  }

  onKeyUp(){
    console.log(this.email);
  }

  onClick(e) {
    e.preventDefault();//se nao colocarmos isto ele volta a pagina default, que tem etapa=1
    //this.id_router=this.id_router+1;
    this.router.navigate(['story']);
  }

  goBack(e) {
    e.preventDefault();
    this.router.navigate(['body']);
  }
}
