import { Injectable } from '@angular/core';
import { BehaviorSubject } from 'rxjs/BehaviorSubject';
import { stringify } from '@angular/core/src/render3/util';


@Injectable()
export class DataService {

    private messageSource = new BehaviorSubject<string>("default message");
    currentMessage = this.messageSource.asObservable();

        constructor() { }

changeMessage(message:string){
    this.messageSource.next(message)
}
}