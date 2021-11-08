import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';
import { HeaderComponent } from './header/header.component';
import { BodyComponent } from './body/body.component';
import { FooterComponent } from './footer/footer.component';
import { StartgameComponent } from './startgame/startgame.component';
import { Routes, RouterModule } from '@angular/router';
import { CookieService } from 'angular2-cookie/services/cookies.service';
import { ContinuegameComponent } from './continuegame/continuegame.component';
import { StoryComponent } from './story/story.component';
import { NoidComponent } from './noid/noid.component';
import { DataService } from './data.service';

const appRoutes: Routes = [
  { path: '', component: BodyComponent },
  { path: 'body', component: BodyComponent },
  { path: 'startgame', component: StartgameComponent },
  { path: 'header', component: HeaderComponent },
  { path: 'footer', component: FooterComponent },
  { path: 'story', component: StoryComponent },
  { path: 'continuegame', component: ContinuegameComponent },
  { path: 'noid', component: NoidComponent }
]

@NgModule({
  declarations: [
    AppComponent,
    HeaderComponent,
    BodyComponent,
    FooterComponent,
    StartgameComponent,
    ContinuegameComponent,
    StoryComponent,
    NoidComponent
  ],
  imports: [
    BrowserModule,
    RouterModule.forRoot(appRoutes)],
  providers: [
    CookieService,
    DataService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
