import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { NoidComponent } from './noid.component';

describe('NoidComponent', () => {
  let component: NoidComponent;
  let fixture: ComponentFixture<NoidComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ NoidComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(NoidComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
