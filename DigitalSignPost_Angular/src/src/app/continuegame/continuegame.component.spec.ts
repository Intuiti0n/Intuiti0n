import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ContinuegameComponent } from './continuegame.component';

describe('ContinuegameComponent', () => {
  let component: ContinuegameComponent;
  let fixture: ComponentFixture<ContinuegameComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ContinuegameComponent]
    })
      .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ContinuegameComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
