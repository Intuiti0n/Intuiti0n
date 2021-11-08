import { Component, OnInit} from '@angular/core';
import { CookieService } from 'angular2-cookie/services/cookies.service';
import { Router } from '@angular/router';
import {DataService}  from '../data.service';
import { Message } from '@angular/compiler/src/i18n/i18n_ast';

@Component({
  selector: 'app-body',
  templateUrl: './body.component.html',
  styleUrls: ['./body.component.css']
})
export class BodyComponent implements OnInit {
  username = this._cookieService.get('username');
  cookieIsThere = false;
  idIsThere = false;
  url_string = window.location.href; //window.location.href
  url = new URL(this.url_string);
  message:string;
  constructor(private router: Router, private _cookieService: CookieService, private data:DataService) { }

  ngOnInit() {
    this.data.currentMessage.subscribe(message => this.message = message);
    //console.log(this.username);//check if username is getting correct
    var id = this.url.searchParams.get("id");
    //console.log(id);//check if parsing url id is correctly done
    this.newMessage(id.toString());
    //parte que necessita de id pra funcionar
    /*
    if (id == undefined) {
      this.idIsThere = false;
      this.router.navigate(['noid']);
    }
    else {
      this.router.navigate(['noid']);
      this.idIsThere = true;
    }
    
    console.log(this.idIsThere);

    if (this.idIsThere == false) {
      this.router.navigate(['noid']);
    }
    else {
      if (this.username != null) {
        this.router.navigate(['continuegame']);
      }
      else {
        this.router.navigate(['']);
        //this.$routeParams.userID
      }
      */
      if (this.username != null) {
        this.router.navigate(['continuegame']);
      }
      else {
        this.router.navigate(['']);
      }
    /*
    pegar no id
    armazenar em variavel
    passar variavel para outras componentes,
    de acordo com a variavel, ler uma etapa
    */
    /*
    
    */
  }

  getCookie(key: string) {
    return this._cookieService.get(key);
  }

  newMessage(message:string){
    this.data.changeMessage(message);
  }

  loginUser(e) {
    e.preventDefault();
    console.log(e);
    var username = e.target.elements[0].value;
    console.log(username);

    if (username != undefined) {
      this.router.navigate(['startgame']);
      this._cookieService.put('username', username);
    }

  }
}
